<template>
  <v-card
    flat
    max-width="700px"
    style="margin: 1em; margin-bottom: 3em; background: transparent"
  >
    <v-card-actions>
      <v-btn
        @click="addSequence"
        icon="mdi-plus"
        color="success"
        variant="tonal"
      ></v-btn>
      <v-select
        style="margin: 1em"
        label="Sequence type"
        hide-details="auto"
        density="comfortable"
        variant="outlined"
        :items="['Array', 'LinkedList']"
        v-model="selected"
      ></v-select>
    </v-card-actions>
  </v-card>
</template>

<script lang="ts">
import config from "@/config";
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "AddSequence",
  setup() {
    const store = useAppStore();
    return { store };
  },
  data: () => ({
    type: "Array",
    selected: "Array",
  }),
  methods: {
    async addSequence() {
      const typeParam = this.selected == "Array" ? "array" : "list";
      const response = await fetch(
        config.backendUrl + "/records?type=" + typeParam,
        {
          method: "POST",
        }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error adding sequence: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
  },
});
</script>
