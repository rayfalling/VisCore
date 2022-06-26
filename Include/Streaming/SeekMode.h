/**
 * Created by Rayfalling on 2022/6/12.
 *
 * SeekMode
 * */

#ifndef VISCORE_SEEK_MODE_H
#define VISCORE_SEEK_MODE_H
#include "VisCoreExport.generate.h"

namespace VisCore::Streaming {
	/**
	 * \brief Seek mode
	 */
	enum class VIS_CORE_EXPORTS SeekMode {
		/**
		 * \brief Seek from special position
		 */
		SeekSet,

		/**
		 * \brief Seek from current position
		 */
		SeekCurrent,

		/**
		 * \brief Seek from end
		 */
		SeekEnd
	};
}

#endif //VISCORE_SEEK_MODE_H