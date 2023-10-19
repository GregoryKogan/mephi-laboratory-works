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
      <h3 style="font-family: monospace">{{ values }}</h3>
    </v-container>

    <AppendCard :index="index" />
    <PrependCard :index="index" />
    <SetCard v-if="values.length > 0" :index="index" />
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

export default defineComponent({
  name: "Sequence",
  components: {
    AppendCard,
    PrependCard,
    SetCard,
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
      this.$router.push({ name: "Home" });
    },
  },
});
</script>
