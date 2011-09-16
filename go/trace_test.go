package fmt

import "testing"

func TestTrace(t *testing.T) {
    tracefn("TestTrace");
    defer untracefn(TestTrace);
}
