-- plugin

local fp = io.popen("env")
if fp then
  print("Environment:")
  print( fp:read("*all") )
  fp:close()
else
  print("could not popen'env'")
end

