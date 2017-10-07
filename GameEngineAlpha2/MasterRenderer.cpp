#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(StaticShader * shader) : shader(shader) 
{
	this->entities = new map<TexturedModel, vector<Entity>*>{};
	this->entity_renderer = new EntityRenderer;

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	createProjectionMatrix();

	entity_renderer = new EntityRenderer{ shader, projectionMatrix };
}

MasterRenderer::MasterRenderer()
: shader(new StaticShader)
{
	this->entities = new map<TexturedModel, vector<Entity>*>{};
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	createProjectionMatrix();

	entity_renderer = new EntityRenderer{ shader, projectionMatrix };
}


MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::render(Light sun, Camera cam)
{
	prepare();

	shader->start();
	shader->loadLight(sun);
	shader->loadViewMatrix(cam);

	//entity_renderer->render(*entities);
	shader->stop();
	entities->clear();
}

void MasterRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0, 0.0f, 0);
}

void MasterRenderer::processEntity(Entity entity)
{
	/* 
	is entity null ? break;
    is entities empty?
		construct vector
		insert entity into vector
		create pair with model and new vector
		insert into entities.
	else we need to find if key/model already exists
		if it does, 
			go to it and access it's vector (which should be empty)
			add entity to vector (should update if we use pointers corretly)
		if it does not
			we need to construct new vector
			add entity to vector
			make pair with key/model and new vector
			insert pair into entities.

	if using point to vector then we also need to make certain to allocate the vector when creating the vector
	*/

	TexturedModel model = entity.getModel();
	if (entities->empty())
	{
		vector<Entity>* t = new vector<Entity>;
		t->push_back(entity);
		//entities->insert(make_pair(model, t));
	}
	else{
		//auto it = entities->find(model);
		//map<TexturedModel, vector<Entity>>::iterator  it = entities->find(model);
		//if (it == entities->end()) )
		//{
		//	//entities[model].push_back(entity);
		//}
		//else
		//{
		//	vector<Entity> t;
		//	t.push_back(entity);
		//	//entities.insert(make_pair(model,t));
		//}
	}
}

glm::mat4 MasterRenderer::createProjectionMatrix()
{

	GLfloat aspectRatio = ::display->getWidth() / ::display->getHeight();
	GLfloat y_scale = (1.0f / glm::tan(glm::radians(FOV / 2.0f))) * aspectRatio;
	GLfloat x_scale = y_scale / aspectRatio;
	GLfloat frustrum_length = F_Plane - N_Plane;

	glm::mat4 matrix{ 1 };
	matrix[0][0] = x_scale;
	matrix[1][1] = y_scale;
	matrix[2][2] = -((F_Plane + N_Plane) / frustrum_length);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * N_Plane * F_Plane) / frustrum_length);
	matrix[3][3] = 0;

	return matrix;
}