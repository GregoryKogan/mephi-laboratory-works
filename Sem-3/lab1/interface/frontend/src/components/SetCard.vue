<template>
  <v-container>
    <v-card :disabled="!(store.records[index].seq.length > 0)">
      <v-card-title>
        set
        <v-icon>mdi-cursor-pointer</v-icon>
      </v-card-title>
      <v-card-actions>
        <v-form
          v-model="form"
          @submit.prevent="form ? set() : () => {}"
          style="width: 100%"
        >
          <v-slider
            v-model="setIndex"
            :disabled="!(store.records[index].seq.length > 1)"
            min="0"
            :max="store.records[index].seq.length - 1"
            step="1"
            :thumb-size="15"
            show-ticks
            color="primary"
            hide-details
          >
            <template v-slot:prepend>index: {{ setIndex }}</template></v-slider
          >
          <v-text-field
            v-model="value"
            :rules="rules"
            label="value"
            max-width="100px"
            density="compact"
            hide-details
            single-line
            type="number"
            variant="outlined"
          ></v-text-field>
        </v-form>
        <v-btn
          icon="mdi-send"
          @click="set"
          :disabled="!form"
          style="margin-left: 0.5em"
        ></v-btn>
      </v-card-actions>
    </v-card>
  </v-container>
</template>

<script lang="ts">
import config from "@/config";
import { useAppStore } from "@/store/app";
import { defineComponent } from "vue";

export default defineComponent({
  name: "PrependCard",
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
    value: null,
    setIndex: 0,
    form: false,
    rules: [
      (v: any) => !!v || "Value is required",
      (v: any) => !isNaN(parseInt(v)) || "Value must be a number",
    ],
  }),
  methods: {
    async set() {
      const response = await fetch(
        config.backendUrl +
          "/records/" +
          this.index +
          "/set?value=" +
          this.value +
          "&index=" +
          this.setIndex,
        { method: "POST" }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error setting value: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
  },
});
</script>
