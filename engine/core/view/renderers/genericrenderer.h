/***************************************************************************
 *   Copyright (C) 2005-2008 by the FIFE Team                              *
 *   http://www.fifengine.de                                               *
 *   This file is part of FIFE.                                            *
 *                                                                         *
 *   FIFE is free software; you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
 ***************************************************************************/

#ifndef FIFE_GENERICRENDERER_H
#define FIFE_GENERICRENDERER_H

// Standard C++ library includes

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "view/rendererbase.h"

namespace FIFE {
	class RenderBackend;
	class AbstractFont;

	class GenericRendererNode {
	public:
		GenericRendererNode(Instance* attached_instance, Location* relative_location, const Point &relative_point = Point(0,0));
		GenericRendererNode(Instance* attached_instance, const Point &relative_point = Point(0,0));
		GenericRendererNode(Location* attached_location, const Point &relative_point = Point(0,0));
		GenericRendererNode(const Point &attached_point);
		~GenericRendererNode();
		
		void setAttached(Instance* attached_instance, const Location &relative_location, const Point &relative_point);
		void setAttached(Instance* attached_instance, const Location &relative_location);
		void setAttached(Instance* attached_instance, const Point &relative_point);
		void setAttached(Instance* attached_instance);
		void setAttached(const Location &attached_location, const Point &relative_point);
		void setAttached(const Location &attached_location);
		void setAttached(const Point &attached_point);
		
		void setRelative(const Location &relative_location);
		void setRelative(const Location &relative_location, Point relative_point);
		void setRelative(const Point &relative_point);
		
		Instance* getAttachedInstance();
		Location* getAttachedLocation();
		Point getAttachedPoint();
		
		Location* getOffsetLocation();
		Point getOffsetPoint();
		
		Instance* getInstance();
		Location* getLocation();
		Point getPoint();

		Point getCalculatedPoint(Camera* cam, Layer* layer, std::vector<Instance*>& instances);
	private:
		Instance* m_instance;
		Location* m_location;
		Point m_point;
	};
	class GenericRendererElementInfo {
	public:
		virtual void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend) { };
		virtual ~GenericRendererElementInfo() {};
	};

	class GenericRendererLineInfo : public GenericRendererElementInfo {
	public:
		GenericRendererNode n1;
		GenericRendererNode n2;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend);
		GenericRendererLineInfo(GenericRendererNode n1, GenericRendererNode n2, uint8_t r, uint8_t g, uint8_t b);
		virtual ~GenericRendererLineInfo() {};
	};
	class GenericRendererPointInfo : public GenericRendererElementInfo {
	public:
		GenericRendererNode n;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend);
		GenericRendererPointInfo(GenericRendererNode n, uint8_t r, uint8_t g, uint8_t b);
		virtual ~GenericRendererPointInfo() {};
	};
	class GenericRendererQuadInfo : public GenericRendererElementInfo {
	public:
		GenericRendererNode n1;
		GenericRendererNode n2;
		GenericRendererNode n3;
		GenericRendererNode n4;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend);
		GenericRendererQuadInfo(GenericRendererNode n1, GenericRendererNode n2, GenericRendererNode n3, GenericRendererNode n4, uint8_t r, uint8_t g, uint8_t b);
		virtual ~GenericRendererQuadInfo() {};
	};
	class GenericRendererImageInfo : public GenericRendererElementInfo {
	public:
		GenericRendererNode n;
		int image;
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend);
		GenericRendererImageInfo(GenericRendererNode n, int image);
		virtual ~GenericRendererImageInfo() {};
	};
	class GenericRendererAnimationInfo : public GenericRendererElementInfo {
	public:
		GenericRendererNode n;
		int animation;
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend);
		GenericRendererAnimationInfo(GenericRendererNode n, int animation);
		virtual ~GenericRendererAnimationInfo() {};
	};
	class GenericRendererTextInfo : public GenericRendererElementInfo {
	public:
		GenericRendererNode n;
		AbstractFont* font;
		std::string text;
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances, RenderBackend* renderbackend);
		GenericRendererTextInfo(GenericRendererNode n, AbstractFont* font, std::string text);
		virtual ~GenericRendererTextInfo() {};
	};
	class GenericRenderer: public RendererBase {
	public:
		/** constructor.
		 * @param renderbackend to use
		 * @param position position for this renderer in rendering pipeline
		 */
		GenericRenderer(RenderBackend* renderbackend, int position);
		
		GenericRenderer(const GenericRenderer& old);
		
		RendererBase* clone();

		/** Destructor.
		 */
		virtual ~GenericRenderer();
		void render(Camera* cam, Layer* layer, std::vector<Instance*>& instances);
		std::string getName() { return "GenericRenderer"; }

		/** Gets instance for interface access
		 */
		static GenericRenderer* getInstance(IRendererContainer* cnt);

		void addLine(GenericRendererNode n1, GenericRendererNode n2, uint8_t r, uint8_t g, uint8_t b);
		void addPoint(GenericRendererNode n, uint8_t r, uint8_t g, uint8_t b);
		void addQuad(GenericRendererNode n1, GenericRendererNode n2, GenericRendererNode n3, GenericRendererNode n4, uint8_t r, uint8_t g, uint8_t b);
		void addText(GenericRendererNode n, AbstractFont* font, std::string text);
		void addImage(GenericRendererNode n, int image);
		void addAnimation(GenericRendererNode n, int animation);
		void removeAll();

	private:
		std::vector<GenericRendererElementInfo*> m_infos;
	};

}

#endif
