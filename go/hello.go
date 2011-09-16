package main

import (
    "fmt"
    "container/vector"
    //"trace"
)

// interface
type Object interface {
    ObjectName() string
}

type AbsList interface {
    ListType() string
}

// NoneList
type NoneList struct {
}

func (this NoneList) ObjectName() string {
    return "Object Name is: NoneList"
}

// FooList
type FooList struct {
}

func (this FooList) ListType() string {
    return "this is FooList"
}

// StudentList
type StudentList struct {
    ClassName string
    StudentName []string
}

func (this *StudentList) CountStudent() int {
    return len(this.StudentName)
}

func (this *StudentList) AppendStudent(name string) {
    var ref = &this.StudentName
    *ref = append(*ref, name)
}

func (this *StudentList) EraseStudent(index int) {
    var ref = &this.StudentName
    var size = len(*ref)
    var newslice = make([]string, size-1)
    copy(newslice[0 : index], (*ref)[0: index])
    copy(newslice[index : size-1], (*ref)[index+1: size])
    *ref = newslice
}

func (this *StudentList) ListType() string {
    return "this is StudentList"
}

// closure
func addhold(beg int) (func(int) int) {
    //trace("addhold")
    //defer untrace("addhold")

    var x int = beg
    return func(delta int) int {
	x += delta
	return x
    }
}

// enter
func main() {
    f := addhold(1);
    fmt.Println(f(1));
    fmt.Println(f(20));
    fmt.Println(f(300));

    list := &StudentList{"class1", []string{"shen", "cai"}}

    list.AppendStudent("yu")
    fmt.Println(list.StudentName)

    list.AppendStudent("wang")
    fmt.Println(list.StudentName)

    list.EraseStudent(list.CountStudent()-1)
    fmt.Println(list.StudentName)

    list.EraseStudent(list.CountStudent()-1)
    fmt.Println(list.StudentName)

    list.EraseStudent(list.CountStudent()-1)
    fmt.Println(list.StudentName)

    list.EraseStudent(0)
    fmt.Println(list.StudentName)

    fmt.Printf("len: %d\n", len(list.StudentName))
    fmt.Printf("cap: %d\n", cap(list.StudentName))

    isAbsList(list)
    isAbsList(FooList{})

    var vec vector.IntVector = []int {1, 2, 3, 4}
    vec.Insert(0, 10)
    fmt.Println(vec)
}

func isAbsList(list AbsList) {
    if _, ok := list.(AbsList); ok {
	fmt.Println(list.ListType())
    } else {
	fmt.Println("not an AbsList")
    }
}
