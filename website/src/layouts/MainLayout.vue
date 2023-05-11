<template>
  <q-layout view="hHh LpR fFf">
    <q-header class="bg-primary text-white" elevated>
      <q-toolbar>
        <q-btn dense flat icon="menu" round @click="toggleLeftDrawer"/>
        <q-toolbar-title>
          <q-avatar>
            <img alt="Icon" src="favicon.ico"/>
          </q-avatar>
          Jerry Control Panel
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
          v-for="endpoint of endpoints.filter((e) => {
            return e.permission === undefined || hasPermission(e.permission);
          })"
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
          <q-menu>
            <div class="row no-wrap q-pa-md">
              <div class="column">
                <div class="text-h6 q-mb-md">Settings</div>
                <q-toggle v-model="mobileData" label="Use Mobile Data"/>
                <q-toggle v-model="bluetooth" label="Bluetooth"/>
              </div>

              <q-separator class="q-mx-lg" inset vertical/>

              <div class="column items-center">
                <q-avatar size="72px">
                  <img src="https://cdn.quasar.dev/img/avatar4.jpg">
                </q-avatar>

                <div class="text-subtitle1 q-mt-md q-mb-xs">John Doe</div>

                <q-btn
                  v-close-popup
                  color="primary"
                  label="Logout"
                  push
                  size="sm"
                />
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

const router = useRouter();
let leftDrawerOpen = ref(false);
let endpoints = [
  {
    name: 'Aliases',
    url: '/aliases',
    icon: 'bookmark',
    permission: 'aliases.add',
  },
  {
    name: 'Prices',
    url: '/prices',
    icon: 'attach_money',
    permission: 'prices.set',
  },
  {
    name: 'Scammers',
    url: '/scammers',
    icon: 'accessible_forward',
    permission: 'scammers.add',
  },
];
let selected = ref('');
for (let endpoint of endpoints) {
  if (router.currentRoute.value.path.startsWith(endpoint.url)) {
    selected.value = endpoint.name;
    break;
  }
}

function toggleLeftDrawer() {
  leftDrawerOpen.value = !leftDrawerOpen.value;
}

function hasPermission(permission) {
  return checkIfAccountHasPermission(permission);
}

function changeSelected(name) {
  selected.value = name;
}
</script>
