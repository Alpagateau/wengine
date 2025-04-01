return {
  nextState = function()
    if State["chap"] ~= 4 then return end
    say("<dl>Tu voulais me dire quelque chose ?<dg>", 3)
    say("\"Oui !\"", 1)
    say("Dis-je avec entousiasme", 2)
  end
}
