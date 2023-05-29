<template>
  <q-card>
    <q-card-section>
      <div class="row">
        <div class="mdi-align-vertical-center text-h6">
          {{ parentValue.name }}
          <q-popup-edit v-if="!props.readonly" v-slot="scope" v-model="parentValue.name" auto-save>
            <q-input v-model="scope.value" autofocus counter dense @keyup.enter="scope.set"/>
          </q-popup-edit>
        </div>
        <q-space/>
        <q-btn v-if="readonly" color="negative" dense flat icon="delete" round @click="emit('remove')"/>
      </div>
    </q-card-section>
    <q-card-section>
      <q-checkbox v-model="parentValue.crossExecution" :disable="props.readonly" label="Cross Execution"/>
    </q-card-section>
    <q-card-section v-if="parentValue.crossExecution">
      <p v-if="readonly" style="text-align: center">Brightness</p>
      <div class="row">
        <q-chip v-for="x of parentValue.brightness" :key="x" :label="x"
                :removable="!props.readonly" @remove="parentValue.brightness.splice(parentValue.brightness.indexOf(x))"></q-chip>
      </div>
      <div v-if="!props.readonly" class="row">
        <q-input v-model="modifyingBrightness" class="q-mr-lg" label="Brightness (%)" style="width: 140px"
                 type="number">
          <template v-slot:append>
            <q-btn :disable="props.readonly" dense
                   flat icon="add" round @click="parentValue.brightness.push(modifyingBrightness * 0.01 * 255)"/>
          </template>
        </q-input>
      </div>
      <p v-if="readonly" style="text-align: center">Scan Times</p>
      <div class="row">
        <q-chip v-for="x of parentValue.scanTimes" :key="x" :label="x"
                :removable="!props.readonly" @remove="parentValue.scanTimes.splice(parentValue.scanTimes.indexOf(x))"></q-chip>
      </div>
      <div v-if="!props.readonly" class="row">
        <q-input v-model="modifyingScanTimes" class="q-mr-lg" label="Scan Times" style="width: 140px"
                 type="number">
          <template v-slot:append>
            <q-btn :disable="props.readonly" dense
                   flat icon="add" round @click="parentValue.scanTimes.push(modifyingScanTimes)"/>
          </template>
        </q-input>
      </div>
      <p v-if="readonly" style="text-align: center">Scan Interval</p>
      <div class="row">
        <q-chip v-for="x of parentValue.scanInterval" :key="x" :label="x"
                :removable="!props.readonly" @remove="parentValue.scanInterval.splice(parentValue.scanInterval.indexOf(x))"></q-chip>
      </div>
      <div v-if="!props.readonly" class="row">
        <q-input v-model="modifyingScanInterval" class="q-mr-lg" label="Scan Interval" style="width: 140px"
                 type="number">
          <template v-slot:append>
            <q-btn :disable="props.readonly" dense
                   flat icon="add" round @click="parentValue.scanInterval.push(modifyingScanInterval)"/>
          </template>
        </q-input>
      </div>
    </q-card-section>
    <q-card-section v-else>
      <q-input v-model="modifying.brightness" :disable="props.readonly" label="Brightness" type="number"
               @update:modelValue="updateSingle('brightness')"></q-input>
      <q-input v-model="modifyingScanTimes" :disable="props.readonly" label="Scan Times" type="number"
               @update:modelValue="updateSingle('scanTimes')"></q-input>
      <q-input v-model="modifying.scanInterval" :disable="props.readonly" label="Scan Interval" type="number"
               @update:modelValue="updateSingle('scanInterval')"></q-input>
    </q-card-section>
    <slot name="append"></slot>
  </q-card>
</template>

<script lang="ts" setup>
import {computed, reactive, ref} from 'vue';

const emit = defineEmits(['update:modelValue', 'remove'])
const props = defineProps(['modelValue', 'readonly'])
const modifyingBrightness = ref(0);
const modifyingScanTimes = ref(0);
const modifyingScanInterval = ref(0);
const modifying = reactive({
  brightness: 0,
  scanTimes: 0,
  scanInterval: 0,
})
const parentValue = computed({
  get() {
    return props.modelValue;
  },
  set(val) {
    emit('update:modelValue', val);
  },
})
console.log(parentValue.value)

function updateSingle(slot: string) {
  const slotTyped = slot as keyof typeof modifying;
  parentValue.value[slot] = [modifying[slotTyped]];
}
</script>
