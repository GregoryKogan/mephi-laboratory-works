<template>
  <h1 v-for="(record, index) in store.records" :key="index">
    {{ index }} - {{ record }}
  </h1>
</template>

<script lang="ts">
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "Home",
  setup() {
    const store = useAppStore();
    return { store };
  },
});
</script>
