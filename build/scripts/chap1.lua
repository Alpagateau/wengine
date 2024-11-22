return {
nextState = function()
  if(State["chap"] ~= 1) then return end 
  if(State["intro"] == nil) then
    State["intro"] = 0
    say("\"Abandon All Hope\"")
    say("\"All Ye Who Enter\"")
    say("That's a weird thing to have on your mat.")
    say("I found myself in front of this door, not knowing what to expect")
  end
  if(State["intro"] == 0) then
    ask(
        {
          {"knock",
            function()
              State["intro"] = 1
              say("Knock knock knock")
            end
          },
          {"read adress", function() say("5 Faust's street") end}
        }
      )
  end
end
}
