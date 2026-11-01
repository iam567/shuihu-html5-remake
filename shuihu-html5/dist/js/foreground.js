/** Original exploration foreground only. Never changes traversal or event data. */
export class OriginalForeground {
  constructor({manifest = {maps: {}}, load, makeCanvas = () => document.createElement('canvas'), timeoutMs = 15000}) {
    this.manifest = manifest;
    this.load = load;
    this.makeCanvas = makeCanvas;
    this.timeoutMs = timeoutMs;
    this.request = 0;
    this.active = null;
    this.status = 'idle';
  }

  async refresh(map) {
    const request = ++this.request;
    this.active = null;
    const record = this.manifest.maps[map?.id];
    if (!record?.mask || record.originalImage !== map.image ||
        record.width !== map.widthPixels || record.height !== map.heightPixels) {
      this.status = 'unavailable';
      return null;
    }
    this.status = 'loading';
    let timer;
    try {
      const [original, mask] = await Promise.race([
        Promise.all([this.load(map.image), this.load(record.mask)]),
        new Promise((_, reject) => {timer = setTimeout(() => reject(new Error('Foreground load timeout')), this.timeoutMs);}),
      ]);
      for (const image of [original, mask]) {
        if (image.naturalWidth !== record.width || image.naturalHeight !== record.height) {
          throw new Error('Foreground image dimensions differ from the original map');
        }
      }
      const surface = this.makeCanvas();
      surface.width = record.width;
      surface.height = record.height;
      const ctx = surface.getContext('2d');
      ctx.imageSmoothingEnabled = false;
      ctx.drawImage(original, 0, 0);
      ctx.globalCompositeOperation = 'destination-in';
      ctx.drawImage(mask, 0, 0);
      ctx.globalCompositeOperation = 'source-over';
      if (request !== this.request) return null;
      this.active = {mapId: map.id, image: map.image, surface};
      this.status = 'ready';
      return this.active;
    } catch (error) {
      if (request === this.request) {
        this.status = 'unavailable';
        this.active = null;
      }
      return null;
    } finally {
      clearTimeout(timer);
    }
  }

  draw(ctx, {map, image = map?.image, camera, battle = false}) {
    const active = this.active;
    // The original silhouette is not a validated HD silhouette; battle priority is separate.
    if (battle || !active || active.mapId !== map?.id || active.image !== image) return false;
    ctx.save();
    ctx.imageSmoothingEnabled = false;
    ctx.drawImage(active.surface, -Math.round(camera.x), -Math.round(camera.y));
    ctx.restore();
    return true;
  }
}
