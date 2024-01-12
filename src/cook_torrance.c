/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cook_torrance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olskor <olskor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:26:07 by olskor            #+#    #+#             */
/*   Updated: 2024/01/12 16:59:35 by olskor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vec3	get_uv_cyl(t_cylinder cylinder, t_Vec3 p)
{
	t_Vec3	uv;
	t_Vec3	n;

	n = unit_vec3(subvec3(p, cylinder.pos));
	uv.x = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	uv.y = 0.5 - asin(n.y) / M_PI;
	return (uv);
}

t_Col	fresnelterm(t_Col F0, float cosA)
{
	float	t;

	t = pow(1 - cosA, 5);
	return (addcol(F0, scalecol(
				addcol(col4(0, 1, 1, 1), scalecol(F0, -1)), t)));
}

t_Col	cook_torrance(t_hit hit, t_Ray ray, t_light light, t_Col lightcol)
{
	t_ct	ct;

	ct.normal = unit_vec3(hit.norm);
	ct.lightdir = unit_vec3(subvec3(light.pos, hit.p));
	ct.viewdir = unit_vec3(subvec3(ray.orig, hit.p));
	ct.halfdir = unit_vec3(addvec3(ct.lightdir, ct.viewdir));
	ct.ndotl = saturate(dot(ct.normal, ct.lightdir));
	ct.ndotv = fabs(dot(ct.normal, ct.viewdir));
	ct.ndoth = saturate(dot(ct.normal, ct.halfdir));
	ct.ldoth = saturate(dot(ct.lightdir, ct.halfdir));
	ct.roughness = max((1 - hit.mat.smooth) * (1 - hit.mat.smooth), 0.002);
	ct.lambdav = ct.ndotl * (ct.ndotv * (1 - ct.roughness) + ct.roughness);
	ct.lambdal = ct.ndotv * (ct.ndotl * (1 - ct.roughness) + ct.roughness);
	ct.v = 0.5f / (ct.lambdav + ct.lambdal + 0.000001);
	ct.a2 = ct.roughness * ct.roughness;
	ct.d = (ct.ndoth * ct.a2 - ct.ndoth) * ct.ndoth + 1.0f;
	ct.dd = (1 / M_PI) * ct.a2 / (ct.d * ct.d + 0.00000001);
	ct.speccolor = lerpcol(col4(1, 0.04, 0.04, 0.04),
			hit.mat.col, hit.mat.metal);
	ct.specularterm = (ct.dd * ct.v * M_PI * ct.ndotl);
	ct.specularterm *= (ct.speccolor.r + ct.speccolor.g + ct.speccolor.b) > 0.0;
	ct.intensity = light.intensity / vec3length2(ct.lightdir);
	ct.col = scalecol(lightcol, ct.intensity);
	return (mulcol(scalecol(ct.col, ct.specularterm),
			fresnelterm(ct.speccolor, ct.ldoth)));
}
