<template>
  <v-container>
    <v-card>
      <v-card-title>
        insert
        <v-icon>mdi-import</v-icon>
      </v-card-title>
      <v-card-actions>
        <v-form
          v-model="form"
          @submit.prevent="form ? insert() : () => {}"
          style="width: 100%"
        >
          <v-slider
            v-model="insertIndex"
            :disabled="!(store.records[index].seq.length > 0)"
            min="0"
            :max="store.records[index].seq.length"
            step="1"
            :thumb-size="15"
            show-ticks
            color="primary"
            hide-details
          >
            <template v-slot:prepend
              >index: {{ insertIndex }}</template
            ></v-slider
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
          @click="insert"
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
  name: "InsertCard",
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
    insertIndex: 0,
    form: false,
    rules: [
      (v: any) => !!v || "Value is required",
      (v: any) => !isNaN(parseInt(v)) || "Value must be a number",
    ],
  }),
  methods: {
    async insert() {
      const response = await fetch(
        config.backendUrl +
          "/records/" +
          this.index +
          "/insert?value=" +
          this.value +
          "&index=" +
          this.insertIndex,
        { method: "POST" }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error inserting value: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
  },
});
</script>
