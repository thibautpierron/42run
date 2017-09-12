/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibautpierron <thibautpierron@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 19:37:16 by thibautpier       #+#    #+#             */
/*   Updated: 2017/08/01 19:47:34 by thibautpier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATOR_CLASS_HPP
# define ANIMATOR_CLASS_HPP

# include <map>
# include "../../libs/glm/matrix.hpp"
# include "../model/Joint.class.hpp"

class Animator {
    public:
        Animator();
        ~Animator();

        void    doAnimation();
        void    update();

    private:
        float                           animationTime();
        void                            increaseAnimationTime();
        std::map<std::string, glm::mat4>     calculateCurrentAnimationPose();
        void        applyPoseToJoints(std::map<std::string, glm::mat4> currentPose,
                    Joint joint, glm::mat4 parentTransform);
                    getPreviousAndNextFrames();
        float       calculateProgression();
        std::map<std::string, glm::mat4>     interpolatePoses();
};

#endif