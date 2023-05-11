<template>
  <q-page padding>
    <div>
      <h3 style="text-align: center" class="q-ma-sm">LED Control</h3>
      <div class="col">
        <div class="row">
          <q-input v-model="red" type="number"
                   :rules="[val => val >= 0 && val <= 255 || 'Must be a number between 0 and 255']"
                   @update:model-value="submit" label="Red" class="col-1"/>
          <q-slider v-model="red" :min="0" :max="255" color="red" @change="submit"
                    class="col-10 justify-center q-ml-md"/>
        </div>
        <div class="row">
          <q-input v-model="green" type="number"
                   :rules="[val => val >= 0 && val <= 255 || 'Must be a number between 0 and 255']"
                   @update:model-value="submit" label="Green" class="col-1"/>
          <q-slider v-model="green" :min="0" :max="255" color="green" @change="submit"
                    class="col-10 justify-center q-ml-md"/>
        </div>
        <div class="row">
          <q-input v-model="blue" type="number"
                   :rules="[val => val >= 0 && val <= 255 || 'Must be a number between 0 and 255']"
                   @update:model-value="submit" label="Blue" class="col-1"/>
          <q-slider v-model="blue" :min="0" :max="255" color="blue" @change="submit"
                    class="col-10 justify-center q-ml-md"/>
        </div>
      </div>
    </div>
  </q-page>
</template>

<script lang="ts" setup>
import {ref} from 'vue';
import {ws, WebSocketEventCodes} from 'boot/websocket';

let red = ref(0);
let green = ref(0);
let blue = ref(0);
//TODO make this sync with other devices
function submit() {
  if (red.value < 0 || red.value > 255) {
    console.error('Invalid red value');
    return;
  }
  if (green.value < 0 || green.value > 255) {
    console.error('Invalid green value');
    return;
  }
  if (blue.value < 0 || blue.value > 255) {
    console.error('Invalid blue value');
    return;
  }
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.DEBUG_SET_LED_BRIGHTNESS.valueOf(),
    data: {r: red.value, g: green.value, b: blue.value}
  }))
}
</script>
