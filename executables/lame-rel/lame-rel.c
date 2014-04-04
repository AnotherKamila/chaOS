int answer = 42;
int zero;  // should go into .bss => be zeroed out

int main() {
    return answer + zero;
}
