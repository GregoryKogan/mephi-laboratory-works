<template>
  <v-card style="margin: 1em">
    <v-card-item>
      <v-card-title>{{ name }}</v-card-title>
      <v-card-subtitle>length: {{ values.length }}</v-card-subtitle>
    </v-card-item>
    <v-card-text style="font-size: larger">{{ values }}</v-card-text>
  </v-card>
</template>

<script lang="ts">
import { useAppStore, SequenceType } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "Sequence",
  setup() {
    const store = useAppStore();
    return { store };
  },
  props: {
    index: {
      type: Number,
      required: true,
    },
  },
  data: () => ({
    values: [] as number[],
    name: "",
  }),
  created() {
    this.values = this.store.records[this.index].seq;
    this.name =
      this.store.records[this.index].type == SequenceType.Array
        ? "Array"
        : "Linked list";
  },
});
</script>
