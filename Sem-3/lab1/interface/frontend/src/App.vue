<template>
  <router-view />
</template>

<script lang="ts">
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "App",
  setup() {
    const store = useAppStore();
    return { store };
  },
  created() {
    this.store.fetchRecords();
  },
});
</script>
