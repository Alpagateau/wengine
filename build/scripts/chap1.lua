return {
nextState = function()
  if(State["chap"] ~= 1) then return end
  if(State["intro"] == nil) then
    State["intro"] = 0
    say("Me voila")
    say("La porte est devant moi.")
    State["toque"] = 0
    while State["toque"] == 0 do
      ask({
          {"Relire l'adresse", function() say("92 rue des Vignoles") end},
          {"Toquer",
          function()
            State["toque"] = 1
          end},
        })
    end
    say(":6A6A6A:Toc. toc. toc.")
    say("")
    --say("I found myself in front of this door, not knowing what to expect")
  end
end
}
