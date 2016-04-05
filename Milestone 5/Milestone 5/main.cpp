#include "SceneGraph.h"

int main(int argc, char** argv) {
	SceneGraph* sg = new SceneGraph();
	sg->Parse("scene1.txt");
	sg->traverse(glm::mat4());//begin traversing
	sg->writeToFile("scene1_results.txt");

	SceneGraph* sg2 = new SceneGraph();
	sg2->Parse("scene2.txt");
	sg2->traverse(glm::mat4());//begin traversing
	sg2->writeToFile("scene2_results.txt");

	//system("pause");
}
