<template>
  <v-container>
    <v-card :disabled="!(store.records[index].seq.length > 0)">
      <v-card-title>
        remove
        <v-icon>mdi-close-circle-outline</v-icon>
      </v-card-title>
      <v-card-actions>
        <v-form
          v-model="form"
          @submit.prevent="form ? remove() : () => {}"
          style="width: 100%"
        >
          <v-slider
            v-model="removeIndex"
            :disabled="!(store.records[index].seq.length > 1)"
            min="0"
            :max="store.records[index].seq.length - 1"
            step="1"
            :thumb-size="15"
            show-ticks
            color="primary"
            hide-details
          >
            <template v-slot:prepend
              >index: {{ removeIndex }}</template
            ></v-slider
          >
        </v-form>
        <v-btn
          icon="mdi-send"
          @click="remove"
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
  name: "RemoveCard",
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
    removeIndex: 0,
    form: false,
    rules: [
      (v: any) => !!v || "Value is required",
      (v: any) => !isNaN(parseInt(v)) || "Value must be a number",
    ],
  }),
  methods: {
    async remove() {
      const response = await fetch(
        config.backendUrl +
          "/records/" +
          this.index +
          "/remove?index=" +
          this.removeIndex,
        { method: "POST" }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error removing value: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }

      this.removeIndex -= 1;
      if (this.removeIndex < 0) this.removeIndex = 0;
    },
  },
});
</script>
