<template>
  <q-layout view="hHh LpR fFf">
    <q-header class="bg-primary text-white" elevated>
      <q-toolbar>
        <q-btn dense flat icon="menu" round @click="toggleLeftDrawer"/>
        <q-toolbar-title>
          <q-avatar>
            <img alt="Icon" src="favicon.ico"/>
          </q-avatar>
          Color Tester
        </q-toolbar-title>
        <q-btn
          dense
          flat
          icon="light_mode"
          round
          style="align-content: end"
          @click="
            $q.dark.toggle();
            $q.localStorage.set('dark', $q.dark.isActive);
          "
        />
      </q-toolbar>
    </q-header>

    <q-drawer v-model="leftDrawerOpen" elevated show-if-above side="left">
      <q-list class="menu-list fit column">
        <q-item
          v-for="endpoint of endpoints"
          :key="endpoint.name"
          v-ripple
          :active="selected === endpoint.name"
          :to="endpoint.url"
          @click="changeSelected(endpoint.name)"
        >
          <q-item-section avatar>
            <q-icon :name="endpoint.icon"/>
          </q-item-section>

          <q-item-section>
            <q-item-label>{{ endpoint.name }}</q-item-label>
          </q-item-section>
        </q-item>
        <q-space/>
        <q-item v-ripple>
          <q-item-section avatar>
            <q-icon name="info"/>
          </q-item-section>

          <q-item-section>
            <q-item-label>Device Info</q-item-label>
          </q-item-section>
          <q-menu class="q-ma-md">
            <div class="row no-wrap q-pa-md" :dummy="refresh">
              <div class="column" v-if="arduinoBoardInfo !== undefined">
                <div class="text-h6 q-mb-md">Arduino</div>
                <p>Uptime: {{ new Date(arduinoBoardInfo.uptime).toISOString().slice(11, 19) }}</p>
              </div>

              <q-separator class="q-mx-lg" inset vertical/>

              <div class="column" v-if="esp32BoardInfo !== undefined">
                <div class="text-h6 q-mb-md">ESP32</div>
                <p>Uptime: {{ new Date(esp32BoardInfo.uptime).toISOString().slice(11, 19) }}</p>
                <p>Temperature: {{ Math.round(esp32BoardInfo.temperature * 10) / 10 }} °C</p>
              </div>

              <q-separator class="q-mx-lg" inset vertical/>

              <div class="column">
                <div class="text-h6 q-mb-md">Module (WIP)</div>
                <p>LED Lightness: </p>
                <p>Photoresistor readings: </p>
              </div>
            </div>
          </q-menu>
        </q-item>
      </q-list>
    </q-drawer>

    <q-page-container>
      <q-page class="row no-wrap">
        <div class="col q-ma-md">
          <div class="column full-height">
            <q-scroll-area class="col q-pa-sm" visible>
              <router-view/>
            </q-scroll-area>
          </div>
        </div>
      </q-page>
    </q-page-container>
  </q-layout>
</template>

<script setup>
import {ref} from 'vue';
import {useRouter} from 'vue-router';
import {arduinoBoardInfo, esp32BoardInfo} from 'boot/websocket';

const router = useRouter();
let leftDrawerOpen = ref(false);
let endpoints = [
  {
    name: 'Scans',
    url: '/scans',
    icon: 'document_scanner',
  },
  {
    name: 'Scan Profiles',
    url: '/profiles',
    icon: 'settings',
  },
  {
    name: 'Debug',
    url: '/debug',
    icon: 'terminal',
  },
];
let selected = ref('');
let refresh = ref(0);

function refreshPage() {
  refresh.value++;
  setTimeout(refreshPage, 1000);
}

refreshPage();

for (let endpoint of endpoints) {
  if (router.currentRoute.value.path.startsWith(endpoint.url)) {
    selected.value = endpoint.name;
    break;
  }
}

function toggleLeftDrawer() {
  leftDrawerOpen.value = !leftDrawerOpen.value;
}

function changeSelected(name) {
  selected.value = name;
}
</script>
