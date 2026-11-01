import test from 'node:test';
import assert from 'node:assert/strict';
import {directionFor} from '../dist/js/joystick.js';
test('analog stick deadzone and cardinal direction selection',()=>{assert.equal(directionFor(4,5),null);assert.equal(directionFor(0,-30),0);assert.equal(directionFor(5,28),1);assert.equal(directionFor(-30,8),2);assert.equal(directionFor(25,-12),3);assert.equal(directionFor(0,0),null);});
