/**
 * 
 */


core = {
	workspaces : [],
	create_workspace : function(elements){
		this.workspaces.add(new ws(elements));	
	},
	ajaxSetup : function(){
		var param;
		for( param in ajaxParams ){
			
		}
	},
	ajaxParams : {},
	ajaxHandlers : [],
	login : function(){
                var newel = document.getElementsByTagName("body");
                this.elements.login = document.createElement("div");

        }
};


ws.prototype = {
	elements : {},
	handlers : [],
	elemArrays : []
	
};

