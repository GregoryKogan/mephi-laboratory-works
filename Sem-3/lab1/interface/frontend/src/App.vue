<template>
  <router-view />
</template>

<script lang="ts">
import { useAppStore, SequenceRecord, SequenceType } from "@/store/app";
import { defineComponent } from "vue";
import config from "@/config";

export default defineComponent({
  name: "App",
  setup() {
    const store = useAppStore();
    return { store };
  },
  async created() {
    const data = await fetch(config.backendUrl + "/records");
    const parsed_data = await data.json();
    let records: SequenceRecord[] = [];
    for (let record_data of parsed_data.records) {
      records.push({
        type:
          record_data.type == "array" ? SequenceType.Array : SequenceType.List,
        seq: record_data.seq,
      });
    }
    this.store.setRecords(records);
  },
});
</script>
