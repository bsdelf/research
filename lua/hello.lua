print("hello shen 你好")

function fact1(n, ret)
    if n == 0 then
	return ret
    else
	return fact1(n-1, n*ret)
    end
end

function fact2(n)
    if n == 0 then
	return 1
    else
	return n * fact2(n-1)
    end
end

print(fact1(100,1))

print("done\n")

[[ifor i=1,5 do
    print(i)
end


file = io.open("build", "r")
for line in file:lines() 
    do 
	print(line)
    end

print("gcinfo:", gcinfo())

local file = io.open("hex", "wb")
magic = "ELF"
file:write(magic)
file:write(string.format("%04x", 10))
file:write(string.format("%04x", 100))
file:close();
]]


