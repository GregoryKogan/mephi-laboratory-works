<template>
  <v-container>
    <v-card :disabled="!(store.records[index].seq.length > 0)">
      <v-card-title>
        get subsequence
        <v-icon>mdi-ray-start-end</v-icon>
      </v-card-title>
      <v-card-text
        v-if="subsequence.length > 0"
        style="font-family: monospace; font-size: large"
        class="text-warning"
        >{{ subsequence }}</v-card-text
      >
      <v-card-actions>
        <v-form
          v-model="form"
          @submit.prevent="form ? get_subsequence() : () => {}"
          style="width: 100%"
        >
          <v-range-slider
            v-model="range"
            :disabled="!(store.records[index].seq.length > 1)"
            min="0"
            :max="count_max_range()"
            step="1"
            color="primary"
            :thumb-size="15"
            show-ticks
            hide-details
            strict
          >
            <template v-slot:prepend>start: {{ range[0] }}</template>
            <template v-slot:append>end: {{ range[1] }}</template>
          </v-range-slider>
        </v-form>
        <v-btn
          icon="mdi-send"
          @click="get_subsequence"
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
  name: "SubsequenceCard",
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
    range: [0, 0],
    subsequence: [],
    form: false,
    rules: [
      (v: any) => !!v || "Value is required",
      (v: any) => !isNaN(parseInt(v)) || "Value must be a number",
    ],
  }),
  methods: {
    async get_subsequence() {
      const response = await fetch(
        config.backendUrl +
          "/records/" +
          this.index +
          "/subsequence?start=" +
          this.range[0] +
          "&end=" +
          this.range[1],
        { method: "GET" }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error setting value: " + msg);
        return;
      } else {
        this.subsequence = (await response.json()).subsequence;
        this.store.fetchRecords();
      }
    },
    count_max_range() {
      if (!this.store.records.length) return 0;
      let mr = this.store.records[this.index].seq.length - 1;
      if (mr < 0) mr = 0;
      if (this.range[0] > mr) this.range[0] = mr;
      if (this.range[1] > mr) this.range[1] = mr;
      return mr;
    },
  },
});
</script>
