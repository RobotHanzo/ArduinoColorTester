<template>
  <q-page padding>
    <q-btn label="New Scan" icon="add" color="positive" @click="dialog = true"/>
    <q-btn label="Query Results" icon="search" color="primary" @click="queryResults()"/>
  </q-page>
  <q-dialog v-model="dialog">
    <q-card>
      <q-card-section>
        <div class="text-h6">Start a new scan</div>
      </q-card-section>
      <q-card-section>
        <q-select v-model="selectedProfileId" label="Profile" :options="options"></q-select>
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
let dialog = ref(false)

function startScan() {
  const generatedProfiles = getProfile(selectedProfileId.value)?.toScanProfile();
  console.log(generatedProfiles)
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.SCHEDULE_SCAN.valueOf(),
    data: {
      name: getProfile(selectedProfileId.value)?.name,
      profiles: generatedProfiles
    }
  }))
}

function queryResults() {
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.QUERY_SCAN_PROGRESS.valueOf(),
    data: {
      name: options[1],
    }
  }))
  ws.send(JSON.stringify({
    eventCode: WebSocketEventCodes.READ_SCAN_RESULT.valueOf(),
    data: {
      name: options[1],
    }
  }))
}
</script>
