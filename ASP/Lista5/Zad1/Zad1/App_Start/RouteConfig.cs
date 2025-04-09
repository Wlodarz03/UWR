using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Zad1
{
    public class RouteConfig
    {

        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            //mamy endpoint ktory zastpuje nam .Add (całe RouteConfig jest generalnie napisane automatycznie)
            // moglibysmy sobie dopisac wlasne endpointy ale tego nie potzebujemy
            // router parsuje dostarczany adres (mozemy zmieniac to parsowanie sciezki)
            /*
             * routes.MapRoute(
                name: "Default",
                url: "{controller}/foo.aspx",
                defaults: new { controller = "Foo", action = "Index", id = UrlParameter.Optional }
            );
             */
            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Start", id = UrlParameter.Optional }
            );
        }
    }
}