<template>
  <v-card @click="goToSequence" style="margin: 1em">
    <h3 style="float: right; padding: 1em">#{{ index + 1 }}</h3>
    <v-card-item>
      <v-card-title>
        <v-icon v-if="name == 'Array'">mdi-code-array</v-icon>
        <v-icon v-else>mdi-link-variant</v-icon>
        {{ name }}
      </v-card-title>
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
      class="text-warning"
      >{{ values }}</v-card-text
    >
    <v-card-actions>
      <v-select
        @click.stop.prevent
        v-model="concatSelection"
        :items="concatChoices"
        label="concat with"
        variant="outlined"
        density="compact"
        hide-details="auto"
        clearable
      ></v-select>
      <v-tooltip text="concat" location="bottom">
        <template v-slot:activator="{ props }">
          <v-btn
            :disabled="
              !concatSelection || !concatChoices.includes(concatSelection)
            "
            v-bind="props"
            @click.stop.prevent="concatSequence"
            icon="mdi-link-plus"
            color="info"
          ></v-btn>
        </template>
      </v-tooltip>
      <v-spacer></v-spacer>
      <v-tooltip text="clear" location="bottom">
        <template v-slot:activator="{ props }">
          <v-btn
            v-bind="props"
            @click.stop.prevent="clearSequence"
            icon="mdi-backspace"
            color="secondary"
          ></v-btn>
        </template>
      </v-tooltip>
      <v-tooltip text="remove" location="bottom">
        <template v-slot:activator="{ props }">
          <v-btn
            v-bind="props"
            @click.stop.prevent="removeSequence"
            icon="mdi-delete"
            color="error"
          ></v-btn>
        </template>
      </v-tooltip>
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
  data: () => ({
    concatSelection: null,
  }),
  computed: {
    values() {
      return this.store.records[this.index].seq;
    },
    name() {
      return this.store.records[this.index].type == SequenceType.Array
        ? "Array"
        : "Linked list";
    },
    concatChoices() {
      const allSeqNames = this.store.records.map((r, index) => {
        return r.type == SequenceType.Array
          ? "Array #" + (index + 1)
          : "Linked list #" + (index + 1);
      });
      const selfChoice = this.name + " #" + (this.index + 1);
      return allSeqNames.filter((name) => name != selfChoice);
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
    async clearSequence() {
      const response = await fetch(
        config.backendUrl + "/records/" + this.index + "/clear",
        {
          method: "POST",
        }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error clearing sequence: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
    async concatSequence() {
      if (!this.concatSelection) return;
      let otherIndex = this.concatChoices.indexOf(this.concatSelection);
      if (otherIndex >= this.index) otherIndex += 1;

      const response = await fetch(
        config.backendUrl +
          "/records/" +
          this.index +
          "/concat?index=" +
          otherIndex,
        {
          method: "POST",
        }
      );
      if (response.status != 200) {
        const msg = await response.text();
        console.error("Error concatenating sequence: " + msg);
        return;
      } else {
        this.store.fetchRecords();
      }
    },
    goToSequence() {
      this.store.fetchRecords();
      this.$router.push({ name: "Sequence", params: { index: this.index } });
    },
  },
});
</script>
