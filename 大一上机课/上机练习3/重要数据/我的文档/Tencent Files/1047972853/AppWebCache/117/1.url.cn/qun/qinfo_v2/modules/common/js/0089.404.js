require.config({paths:{simple:"http://1.url.cn/jslib/simple/6/simple.min",modules:"../../../modules",bower_components:"../../../bower_components"},shim:{simple:{exports:"$"}}});require(["./log","./proj_cfg"],function(LOG,cfg){var businessCfg=cfg.businessCfg;LOG({type:"fail",msg:"File Load Error:404.html",url:window.location.href,mid:businessCfg.page_404_mid})});