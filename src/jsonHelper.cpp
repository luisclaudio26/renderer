#include "../include/jsonHelper.h"

namespace Renderer
{
	namespace JSONHelper
	{
		glm::vec4 vec4FromJSON(const nlohmann::json& in)
		{
			glm::vec4 out;
			out.x = in[0].get<double>();
			out.y = in[1].get<double>();
			out.z = in[2].get<double>();
			out.w = in[3].get<double>();
			return out;
		}

		glm::vec3 vec3FromJSON(const nlohmann::json& in)
		{
			glm::vec3 out;
			out.x = in[0].get<double>();
			out.y = in[1].get<double>();
			out.z = in[2].get<double>();
			return out;
		}

		glm::vec2 vec2FromJSON(const nlohmann::json& in)
		{
			glm::vec2 out;
			out.x = in[0].get<double>();
			out.y = in[1].get<double>();
			return out;
		}

		glm::mat4 parseTransformations(const nlohmann::json& in)
		{
			glm::mat4 out(1.0f);
			glm::mat4 scl(1.0f), rot(1.0f), trans(1.0f);

			if( in.find("scale") != in.end() )
			{
				glm::vec3 scl_v = JSONHelper::vec3FromJSON( in["scale"] );
				scl = glm::scale(scl_v);
			}

			if( in.find("rotate") != in.end() )
			{
				glm::vec4 rot_v = JSONHelper::vec4FromJSON( in["rotate"] );
				rot = glm::rotate(rot_v[3], glm::vec3(rot_v));
			}

			if( in.find("translate") != in.end() )
			{
				glm::vec3 trans_v = JSONHelper::vec3FromJSON( in["translate"] );
				trans = glm::translate(trans_v);
			}

			std::string order = in["order"].get<std::string>();
			for(auto t = order.begin(); t != order.end(); ++t)
			{
				if(*t == 't' || *t == 'T')
					out = trans * out;
				if(*t == 'r' || *t == 'R')
					out = rot * out;
				if(*t == 's' || *t == 'S')
					out = scl * out;
			}

			return out;
		}
	}
}
