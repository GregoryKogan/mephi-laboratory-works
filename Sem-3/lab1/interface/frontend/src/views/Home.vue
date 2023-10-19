<template>
  <AddSequence />
  <SequenceCard v-for="index in reversedIndexes" :key="index" :index="index" />
</template>

<script lang="ts">
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";
import SequenceCard from "@/components/SequenceCard.vue";
import AddSequence from "@/components/AddSequence.vue";

export default defineComponent({
  name: "Home",
  components: {
    SequenceCard,
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
