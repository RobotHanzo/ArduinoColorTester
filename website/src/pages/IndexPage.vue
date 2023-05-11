<template>
  <q-page class="row items-center justify-evenly">
    <q-color v-model="color" @change="submit"/>
  </q-page>
</template>

<script lang="ts" setup>
import {ref} from 'vue';
import {ws, WebSocketEventCodes} from 'boot/websocket';

let color = ref('#000000');

function hexToRgb(hex: string) {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}

function submit() {
  const c = hexToRgb(color.value);
  if (!c) {
    console.error('Invalid color');
    return;
  }
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.DEBUG_SET_LED_BRIGHTNESS.valueOf(),
    data: {r: c.r, g: c.g, b: c.b}
  }))
}
</script>
