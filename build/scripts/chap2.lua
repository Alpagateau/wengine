return {
  nextState = function()
    if State["chap"] ~= 2 then return end
    if State["kettle"] == nil then
      loadImg("kettle.tsi")
      State["kettle"] = 0
      clr()
      -- TODO Add clear screen
    end
  end
}
