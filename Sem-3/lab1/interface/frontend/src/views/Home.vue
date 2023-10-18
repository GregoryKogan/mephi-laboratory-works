<template>
  <AddSequence />
  <Sequence v-for="index in reversedIndexes" :key="index" :index="index" />
</template>

<script lang="ts">
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";
import Sequence from "@/components/Sequence.vue";
import AddSequence from "@/components/AddSequence.vue";

export default defineComponent({
  name: "Home",
  components: {
    Sequence,
    AddSequence,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
  computed: {
    reversedIndexes() {
      return this.store.records.map((_, index) => index).reverse();
    },
  },
});
</script>
