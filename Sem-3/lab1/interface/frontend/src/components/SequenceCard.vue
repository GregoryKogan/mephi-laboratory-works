<template>
  <v-card @click="goToSequence" style="margin: 1em">
    <v-card-item>
      <v-card-title>{{ name }}</v-card-title>
      <v-card-subtitle>length: {{ values.length }}</v-card-subtitle>
    </v-card-item>
    <v-card-text
      style="
        font-family: monospace;
        font-size: large;
        white-space: nowrap;
        word-break: normal;
        overflow: hidden;
        text-overflow: ellipsis;
      "
      >{{ values }}</v-card-text
    >
    <v-card-actions>
      <v-spacer></v-spacer>
      <v-btn
        @click="removeSequence"
        icon="mdi-delete"
        color="error"
        variant="tonal"
      ></v-btn>
    </v-card-actions>
  </v-card>
</template>

<script lang="ts">
import config from "@/config";
import { useAppStore, SequenceType } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "SequenceCard",
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
  computed: {
    values() {
      return this.store.records[this.index].seq;
    },
    name() {
      return this.store.records[this.index].type == SequenceType.Array
        ? "Array"
        : "Linked list";
    },
  },
  methods: {
    async removeSequence() {
      const response = await fetch(
        config.backendUrl + "/records/" + this.index,
        {
          method: "DELETE",
        }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error removing sequence: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
    goToSequence() {
      this.$router.push({ name: "Sequence", params: { index: this.index } });
    },
  },
});
</script>
