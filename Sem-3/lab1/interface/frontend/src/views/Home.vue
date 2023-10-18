<template>
  <Sequence
    v-for="(record, index) in store.records"
    :key="index"
    :index="index"
  />
</template>

<script lang="ts">
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";
import Sequence from "@/components/Sequence.vue";

export default defineComponent({
  name: "Home",
  components: {
    Sequence,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
});
</script>
