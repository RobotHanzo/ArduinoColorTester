<template>
  <q-page padding>
    <div class="q-mb-lg">
      <q-btn class="q-mr-lg" color="positive" icon="add" label="New Scan" @click="dialog = true"/>
      <q-btn color="primary" icon="refresh" label="Refresh" @click="refresh()"/>
    </div>
    <div class="row">
      <q-card v-for="name of $scanResultNames.value" :key="name" class="col-3 q-ma-md">
        <q-card-section>
          <div class="text-h6">{{ name }}</div>
        </q-card-section>
        <q-card-actions align="right">
          <q-btn color="primary" flat label="Download" @click="download(name)"/>
        </q-card-actions>
      </q-card>
      <q-card v-for="name of $scanProgress.queue" :key="name" class="col-3 q-ma-md">
        <q-card-section>
          <div class="text-h6">{{ name }}</div>
        </q-card-section>
        <q-card-section v-if="$scanProgress.current == name">
          {{ ($scanProgress.progress * 100).toFixed(2) }}%
        </q-card-section>

        <q-linear-progress :indeterminate="$scanProgress.current != name" :value="$scanProgress.progress" animationSpeed="250" class="q-mb-none"/>
      </q-card>
    </div>
  </q-page>
  <q-dialog v-model="dialog">
    <q-card>
      <q-card-section>
        <div class="text-h6">Start a new scan</div>
      </q-card-section>
      <q-card-section>
        <q-select v-model="selectedProfileId" :options="options" label="Profile" @update:modelValue="name = selectedProfile.name"></q-select>
        <q-input v-model="name" label="Name" :rules="[val => !!val || 'Name is required']"></q-input>
      </q-card-section>
      <q-card-section>
        <scan-profile-component v-model="selectedProfile" :readonly="true"/>
      </q-card-section>
      <q-card-actions align="right">
        <q-btn color="negative" flat label="Cancel" @click="dialog = false"></q-btn>
        <q-btn color="positive" flat label="Start" @click="startScan();dialog = false"></q-btn>
      </q-card-actions>
    </q-card>
  </q-dialog>
</template>

<script lang="ts" setup>
import {computed, ref} from 'vue';
import ScanProfileComponent from 'components/ScanProfileComponent.vue';
import {ComprehensiveScanProfile} from 'components/ComprehensiveScanProfile';
import {WebSocketEventCodes, ws} from 'boot/websocket';

let profiles = JSON.parse(localStorage.getItem('profiles') || '[]');
const options: string[] = []
for (let profile of profiles) {
  options.push(profile.name)
}

function getProfile(name: string): ComprehensiveScanProfile | null {
  for (let profile of profiles) {
    if (profile.name == name) {
      return ComprehensiveScanProfile.fromJson(profile)
    }
  }
  return null
}

let selectedProfileId = ref(options[0]);
const selectedProfile = computed(() => {
  return getProfile(selectedProfileId.value)
})
let name = ref(selectedProfile.value?.name);
let dialog = ref(false)

function startScan() {
  const generatedProfiles = getProfile(selectedProfileId.value)?.toScanProfile();
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.SCHEDULE_SCAN.valueOf(),
    data: {
      name: name.value,
      profiles: generatedProfiles
    }
  }))
}

function refresh() {
  try {
    ws.send(JSON.stringify({
      eventCode: WebSocketEventCodes.LIST_SCAN_RESULTS.valueOf()
    }))
  } catch (e) {
    console.error(e)
    setTimeout(refresh, 1000);
  }
}

function download(name: string) {
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.READ_SCAN_RESULT.valueOf(),
    data: {
      name: name
    }
  }))
}

refresh()
</script>
