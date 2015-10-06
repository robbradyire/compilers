int main() {
    int numbers[] = {1, 4, 3, 6, 2};

    int i, j, swap;
    for (i = 0; i < 5; i++) {
        for (j = i + 1; j < 5; j++) {
            if (numbers[j] < numbers[i]) {
                swap = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = swap;

            }

        }

    }
    return numbers[0];

}
