package trace

import "fmt"

func tracefn(s string) {
    fmt.Println("entering: %s", s)
}

func untracefn(s string) {
    fmt.Println("leaving: %s", s);
}

