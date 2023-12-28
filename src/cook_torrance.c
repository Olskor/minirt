/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cook_torrance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:26:07 by olskor            #+#    #+#             */
/*   Updated: 2023/12/27 14:09:45 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Col	FresnelTerm(t_Col F0, float cosA)
{
	float	t = pow(1 - cosA, 5);
    return addcol(F0, scalecol(addcol(col4(0, 1, 1, 1), scalecol(F0, -1)), t));
}

t_Col	cook_torrance(t_hit hit, t_Ray ray, t_light light, t_Col lightcol)
{
	t_Vec3	normal   = unit_vec3(hit.norm);
	t_Vec3	lightDir = unit_vec3(subvec3(light.pos, hit.p));
	t_Vec3	viewDir  = unit_vec3(subvec3(ray.orig, hit.p));
	t_Vec3	halfDir  = unit_vec3(addvec3(lightDir, viewDir));

	float	NdotL = saturate(dot(normal, lightDir));
	float	NdotV = fabs(dot(normal, viewDir));
	float	NdotH = saturate(dot(normal, halfDir));
	float	LdotH = saturate(dot(lightDir, halfDir));
	float	perceptualRoughness = 1 - hit.mat.smooth;
	float	roughness = max(perceptualRoughness * perceptualRoughness, 0.002);
	float	roughnessSqr = roughness * roughness;

	float	lambdaV = NdotL * (NdotV * (1 - roughness) + roughness);
	float	lambdaL = NdotV * (NdotL * (1 - roughness) + roughness);
	float	V = 0.5f / (lambdaV + lambdaL + 0.000001);

	float	a2 = roughness * roughness;
    float	d = (NdotH * a2 - NdotH) * NdotH + 1.0f;
    float	D = (1 / M_PI) * a2 / (d * d + 0.00000001);

	float	oneMinusReflectivity = 1 - hit.mat.metal;
	t_Col	specColor = lerpcol(col4(1, 0.04, 0.04, 0.04), hit.mat.col, hit.mat.metal);

	float	specularterm = (0, D * V * M_PI * NdotL);

	specularterm *= (specColor.r + specColor.g + specColor.b) > 0.0;

	float	intensity = light.intensity / vec3length2(lightDir);
	t_Col	col = scalecol(lightcol, intensity);

	t_Col	color = mulcol(scalecol(col, specularterm), FresnelTerm(specColor, LdotH));
	return (color);
}
