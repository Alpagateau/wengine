return {
    nextState = function()
      say("Counting : "..State["val"])
      State["val"]=State["val"]+1
      ask({
      {
        msg = "Hello world",
        method=function ()
          print("[LUA] Hello world from ask")
        end
      }
      })
    end
}
