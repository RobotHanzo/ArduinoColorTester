<template>
  <q-page padding>
    <div class="row" :dummy="dummy">
      <div v-for="(x, i) in profiles" :key="x" class="q-pa-sm">
        <scan-profile-component class="col-3" :readonly="true" v-model="profiles[i]"
                                @remove="profiles.splice(i, 1);saveProfiles()"/>
      </div>
    </div>
    <q-btn color="positive" @click="addProfile" icon="add" round fab fixed right="20px" bottom="20px"/>
  </q-page>
  <q-dialog persistent v-model="addDialogRef">
    <scan-profile-component v-model="editingProfile">
      <template v-slot:append>
        <q-card-actions align="right">
          <q-btn flat color="negative" @click="addDialogRef = false" label="Cancel"/>
          <q-btn flat @click="addDialogRef = false;profiles.push(editingProfile);saveProfiles()" label="Add"
                 color="primary"/>
        </q-card-actions>
      </template>
    </scan-profile-component>
  </q-dialog>
</template>

<script lang="ts" setup>
import ScanProfileComponent from 'components/ScanProfileComponent.vue';
import {Dialog} from 'quasar';
import {ComprehensiveScanProfile} from 'components/ComprehensiveScanProfile';
import {ref} from 'vue';

let profiles = JSON.parse(localStorage.getItem('profiles') || '[]');
let editingProfile = ref(new ComprehensiveScanProfile());
let addDialogRef = ref(false);
let dummy = ref(false);

function saveProfiles() {
  localStorage.setItem('profiles', JSON.stringify(profiles));
  dummy.value = !dummy.value;
}

function addProfile() {
  Dialog.create({
    title: 'Add Profile',
    message: 'Enter a name for the new profile',
    prompt: {
      model: '',
      isValid: (val: string) => val.length > 0
    },
    cancel: true,
    persistent: true
  }).onOk((data: string) => {
    editingProfile.value = new ComprehensiveScanProfile();
    editingProfile.value.name = data;
    addDialogRef.value = true;
  })
}
</script>
