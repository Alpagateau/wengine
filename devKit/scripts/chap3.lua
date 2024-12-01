return {
  nextState = function()
    say("never gonna ..", 1)
      ask({
      {"Give you up",
          function()
            say("YAYY", 2)
            State["rick"] = 1
          end
        },
      {"Let you down", function() say("NAYY", 2) end}
      })
    say("Goodbye", 2)
    State["fin"] = true
  end
}
