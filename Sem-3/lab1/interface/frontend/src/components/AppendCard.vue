<template>
  <v-container>
    <v-card>
      <v-card-title>
        append
        <v-icon>mdi-ray-end</v-icon>
      </v-card-title>
      <v-card-actions>
        <v-form
          v-model="form"
          @submit.prevent="form ? append() : () => {}"
          style="width: 100%"
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
          @click="append"
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
  name: "AppendCard",
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
    form: false,
    rules: [
      (v: any) => !!v || "Value is required",
      (v: any) => !isNaN(parseInt(v)) || "Value must be a number",
    ],
  }),
  methods: {
    async append() {
      const response = await fetch(
        config.backendUrl +
          "/records/" +
          this.index +
          "/append?value=" +
          this.value,
        { method: "POST" }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error appending value: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
  },
});
</script>
