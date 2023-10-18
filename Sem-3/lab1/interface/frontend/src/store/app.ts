// Utilities
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
    }
  },
});
