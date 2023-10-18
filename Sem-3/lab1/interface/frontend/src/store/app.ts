// Utilities
import config from '@/config';
import { defineStore } from 'pinia';

export enum SequenceType {
  Array,
  List,
}

export interface SequenceRecord {
  type: SequenceType;
  seq: number[];
}

export const useAppStore = defineStore('app', {
  state: () => ({
    records: [] as SequenceRecord[],
  }),
  actions: {
    setRecords(records: SequenceRecord[]) {
      this.records = records;
    },

    async fetchRecords() {
      const data = await fetch(config.backendUrl + "/records");
      const parsed_data = await data.json();
      const records: SequenceRecord[] = [];
      for (const record_data of parsed_data.records) {
        records.push({
          type:
            record_data.type == "array"
              ? SequenceType.Array
              : SequenceType.List,
          seq: record_data.seq,
        });
      }
      this.setRecords(records);
    },
  },
});
