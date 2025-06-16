#include "ResourceStructure.h"

namespace minerals{
	ResourceStructure::ResourceStructure(int x, int y): Structure(x,y){
		harvested=false;
		inner_timer=0.0f;
		needs_remove=false;
	}
	bool ResourceStructure::harvest(){
		bool success=false;
		if(harvested==false){
			success=true;
			harvested=true;
		}
		return success;
		
	}
	bool ResourceStructure::get_harvested() const{
		return harvested;
	}
	bool ResourceStructure::get_needs_remove() const{
		return needs_remove;
	}
}