<template>
  <v-container v-if="store.records.length > index">
    <h1>{{ name }}</h1>
    <h3>length: {{ values.length }}</h3>

    <v-btn
      @click="goToHome"
      prepend-icon="mdi-arrow-left-circle"
      style="margin-top: 1em"
      >Go back</v-btn
    >

    <v-container>
      <h3 style="font-family: monospace" class="text-warning">{{ values }}</h3>
    </v-container>

    <AppendCard :index="index" />
    <PrependCard :index="index" />
    <InsertCard :index="index" />
    <SetCard :index="index" />
    <RemoveCard :index="index" />
    <SubsequenceCard :index="index" />
  </v-container>
  <v-container v-else class="fill-height">
    <v-responsive class="align-center text-center fill-height">
      <v-card
        title="Sequence not found"
        subtitle="The sequence you are looking for does not exist."
      >
        <v-card-actions>
          <v-btn @click="goToHome" prepend-icon="mdi-arrow-left-circle"
            >Go back</v-btn
          >
        </v-card-actions>
      </v-card>
    </v-responsive>
  </v-container>
</template>

<script lang="ts">
import { SequenceType, useAppStore } from "@/store/app";
import { defineComponent } from "vue";
import AppendCard from "@/components/AppendCard.vue";
import PrependCard from "@/components/PrependCard.vue";
import SetCard from "@/components/SetCard.vue";
import InsertCard from "@/components/InsertCard.vue";
import RemoveCard from "@/components/RemoveCard.vue";
import SubsequenceCard from "@/components/SubsequenceCard.vue";

export default defineComponent({
  name: "Sequence",
  components: {
    AppendCard,
    PrependCard,
    SetCard,
    InsertCard,
    RemoveCard,
    SubsequenceCard,
  },
  setup() {
    const store = useAppStore();
    return { store };
  },
  data: () => ({
    index: 0,
  }),
  created() {
    this.index = Number(this.$route.params.index);
  },
  computed: {
    values() {
      return this.store.records.length
        ? this.store.records[this.index].seq
        : [];
    },
    name() {
      if (!this.store.records.length) return "";
      return this.store.records[this.index].type == SequenceType.Array
        ? "Array"
        : "Linked list";
    },
  },
  methods: {
    goToHome() {
      this.store.fetchRecords();
      this.$router.push({ name: "Home" });
    },
  },
});
</script>
