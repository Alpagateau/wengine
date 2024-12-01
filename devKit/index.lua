
-- You should have to only modify this
-- Add your scripts here
local imports = {
  require("scripts/chap1"),
  require("scripts/chap2"),
  require("scripts/chap3")
}

-- Global values you can use everywhere if you so wish
State = {
  name = "Anon",
  fin = false,
  chap = 3
}

function NextState()
  if State["fin"]==true then return end
  for key,value in pairs(imports) do
    if value.nextState ~= nil then
      value.nextState()
    end
  end
end

function say(msg, time)
  print("SAYING | "..msg)
  Sleep(time)
end

function ask(tab)
  if State["fin"]==true then return false end
  for key, value in pairs(tab) do
    print(key..") "..value[1])
  end
  local s = io.read("*n")

  tab[s][2]()
  return true
end

function loadImg(msg)
  print("DEBUG : loaded "..msg)
end

function clr()
  print("DEBUG : Cleared screen")
end

function Sleep (a)
    local sec = tonumber(os.clock() + a)
    while (os.clock() < sec) do
    end
end

while State["fin"] ~= true do
  NextState()
end

