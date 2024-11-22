
A = 0
while A < 50 do
  say("Couting to "..A.." <smiley>")
  A = A+1
  if (A - math.floor(A/3)*3) == 2 then
    ask({
      {
        "Decrement by 3",
        function()
          print("[LUA] Opt 1 Choosen")
          A = A - 3
        end
      },
      {
        "Add 1",
        function()
          print("[LUA] Opt 2 Choosen")
        end
      }
    })
  end
end
