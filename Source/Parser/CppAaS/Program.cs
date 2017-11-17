using Microsoft.AspNetCore;
using Microsoft.AspNetCore.Hosting;

namespace CppAaS
{
    public class Program
    {
        public static void Main(string[] args)
        {
            // TODO:
            // 1. parse input
            // 2. determine - cmdline or REST server?
            // 3. import code "context"
            // 4. run through processor/interpretter
            // 5. output with processor/formatter, respective to where
            // input came from and how it is configured
            BuildWebHost(args).Run();
        }

        public static IWebHost BuildWebHost(string[] args) =>
            WebHost.CreateDefaultBuilder(args)
                .UseStartup<Startup>()
                .Build();
    }
}
