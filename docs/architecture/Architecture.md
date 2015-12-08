
Descripción de la arquitectura Metta 

Metta es un sistema operativo exo-cortical que cumple las siguientes funciones: memoria externa y agente de interacción social. Las características recién mencionadas son tareas primordiales, además de la asistencia móvil y la asistencia multimedia. 

El sistema operativo debe proveer medios para tant compartir como recopilar información de relevancia a ud. A este procedimiento lo denominamos "Exo-corteza".

El sistema operativo debe ser un asistente para recopilar información que permita tanto recibir como filtrar, clasificar y mostrar datos de interés y en la manera más cómoda que sea posible.

El sistema operativo debe ser un asistente para compartir información que permita el especificar niveles de privacidad así como distribuir almacenamiento confiable y publicar directamente a sus pares y a otros medios.

Con la finalidad de entregar servicios de almacenamento, gestión y recopilación de información de manera segura sostenemos el siguiente conjunto de principios:

Debe ser posible la labor de distribuir trabajos y almacenarlos fluidamente entre nodos de confianza en la red del usuario. 

Debe ser posible el agregar o quitar nodos de forma sencilla de la red de confianza. 

Debe ser sincroniada la información entre los nodos, cada vez que sea posible.

No debe ser posible que un nodo caiga de la red por medio de la sobresaturación de trabajo, la Calidad de Servicio (de las siglas en inglés "QoS" para "Quality of Service") es fundamental. 

El almacenamiento de datos debe ser asociativo en vez de jerárquico. Los enlaces cruzados entre nodos deben ser realizados mediante relación semántica entre datos. 
Su información debe ser redundante, altamente disponible y almacenada con seguridad. A este concepto lo denominamos bajo la frase "Publique una vez, comparta en todos lados". 
El procesamiento de multimedia y datos significativos en o semántico deberá ser rápido. 

Los principios relativos a los aspectos técnicos del sistema operativo Metta son los siguientes:

La gestión de calidad o "QoS management" ocurrirá en todos los niveles del sistema. Los agentes deben ser capaces de negociar  los recursos que hagan falta y el sistema operativo debe mantener las garantías prometidas a cada recurso. 

La implementación de un sistema altamente compartimentalizado y que se comporte como una caja de arena. Cuando se ejecuta agentes para el servicio a otros usuarios se vuelve fundamental el hecho de proveer seguridad de datos para cada uno de los usarios.  

Baja saturación en la gestión del sistema. La tecnología de un espacio de direcciones permite que sean evitadas operaciones costosas en recursos tales como copia de datos, las cuales son realizadas en el espacio de usuario y a la mayor velocidad que sea posible.

Diagrama de la arquitectura en el sistema operativo Metta

Políticas de bajo y alto nivel diseñadas a la vez.

La arquitectura es separada en mecanismos y políticas. Las políticas son separadas posteriormente en dependientes de mecanismos e independientes.

El arco de mecanismos permite la definición a bajo nivel para construir tanto bloques como protocolos, proceso el cual describe cómo son implementados los nodos. Dichos nodos no son estrictamente reforzados y podría variar el grado de interoperabilidad alcanzado entre nodos. Por ejemplo, el modo administrado conocido como Horizon bitcode based implementation).


Mecanismos:

Un sólo espacio de direcciones por nodo, debido a la existencia de diferentes tamaños en la memoria por nodos y sobrecarga en el mantenimiento espacios de espacios de direcciones y su sincronización entre todos los nodos

Eventos y secuenciadores entregados por un mecanismo de sincronización fundamental (Events provide base sync mechanism) 

Interfaz VP 

Subsistema gráfico 

AGG 

blitjit 

Una política para definir el comportamiento de los nodos y una especificación Metta formal para la interacción de los múltiples nodos.

Diferentes políticas construidas en parte debido a mecanismos posteriormente separados en dos partes: zona inferior dependiente del sistema y zona superior la cual será compilada sobre la zona inferior la cual no depende del mecanismo. 

La política de los nodos definirá la zona inferior de protocolos de interoperabilidad entre nodos. Se define que tipo de datos y aplicaciones serán compartidos, así como se definirá la extensión de la tolerancia a fallos, almacenamiento de datos y la procección del almacenamiento de datos.

La política de nodos incluirá lo siguiente:

Sincronización del almacenamiento 

La política de interfaz de usuario definirá detalles de la interacción con el usuario tanto como perfiles de actividad y que tan a menudo el usuario será interrumpido en cada estado del sistema.


Las partes de la política de interfaz de usuario son enumeradas a continuación:

Línea de comandos (teclas F1 o ESC) 

Interacción con el entorno 

Filosofía de implementación

El núcleo en modo privilegiado será tan pequeño como sea posible. Si determinado software puede ser ejecutado a nivel de usuario, entonces así será. Debido a motivos de seguridad y reconfigurabilidad, el área que se ejecuta con privilegios que podría ser ejecutada globalmente o ejecutada con el máximo de permisos deberá ser minimalista. 

La interposición flexible de servicios de uso común permitirá que el sistema pueda ser flexible sin duplicado significativoe datos, por ejemplo, los métodos de la interfaz pueden ser extendidos sin manipular la implementación original. 

Serán ejecutadas múltiples tareas multimedia de manera eficiente y en tiempo real sin sacrificar la interactividad o el procesamiento. La Calidad de Servicio, QoS como dijimos anteriormente es importante en los tiempos de computación en la nube y computación "swarm" en las cuales los agentes realizan migraciones entre nodos. Los nodos deberán ser capaces de gestionar la carga de datos en la entrada , sea información o programas ejecutables. Las cuotas de QoS deberán /should be possible to enforce by some controlling entities, para mantener el nodo lejos de ser sobresaturado por agentes maliciosos o datos inválidos. 
Disminuir el QoS crosstalk así como entregar ciertas garantías de QoS a las aplicaciones.

Protección de datos entre tareas debido a código poco fiable descargado de internet for carrying out some tasks. Aislamiento de tareas o grupos de las mismas en un entorno tipo caja de arena. El uso de cajas de arena es relevante en el aislamiento  de código poco fiable. La interposición selectiva de interfaces podrá ser de ayuda mediante la entrega de implementaciones adjuntadas a través de cajas de arena. 

El sistema es construido a través de componentes granulados sin privilegios de administración, los cuales son enlazados mediante interfaces.

Los componentes fundamentales de la computación fiable (del inglés Trusted Computing) deben proveer mecanismos y no políticas. Las políticas pueden ser especificadas en niveles superiores. Los sistemas móviles pueden ser fácilmente reconfigurados, si bien sólo en niveles superiores es factible la toma de decisiones acerca de las políticas adecuadas en casos específicos para la posterior autoconfiguración del sistema de manera tal que sea posible la adaptación al entorno. 

El uso libre de Just In Time para realizar optimización en el instante. Relieve programmer from the burden. 


Arquitectura general

El sistema operativo Metta se implementa en un único espacio de Direcciones con fines de gestión de QoS mediante las tecnologías usadas en el sistema operativo Nemesis el cual conforma parte del proyecto Pegasus dentro de los laboratorios de la Universidad de  Cambridge.

La implementación consiste en kickstart, código "glue", componentes de computación fiable, componentes de biblioteca y aplicaciones. Las Aplicaciones son integradas verticalmente, llevan a cabo la mayor parte de la gestión con cualidades tales como alta adaptabilidad y mantención de garantías QoS mediante la eliminación del almacenamiento en servicios comúnmente llevados por el sistema operativo, dicho almacenamiento produce cuellos de botella a menudo.


Espacio Único de Direcciones

El espacio de memoria virtual en el sistema operativo Metta es único y compartido por todos los procesos, lo cual implica que todo mapeo de memoria físico es equivalente al espacio de memoria virtual.

Uno o más dominios podrían ser partes del mismo dominio de protección, lo cual implica que tendremos dominios con los mismos privilegios de acceso a idénticos rangos de espacios de direcciones.

Domain may be part of more than one protection domains. This allows easy sharing by specifying protection domains at the stretch level and by adding domains using the same stretch into the same protection domain.
Implementation detail: on x86, for efficiency there is only one page directory and access rights for the memory frame correspond to global stretch access rights. Once the domain is activated and tries to perform operation not allowed by the global rights, it will fault and the fault handler will then check, if protection domain has more rights actually, in this case the page directory will be updated with new rights and the stretch these frames belong to will be added to a "altered stretches" list for the domain.

Stretches

Any domain may request a stretch from a stretch allocator, specifying the desired size and (optionally) a starting address and attributes. Should the request be successful, a new stretch will be created and returned to the caller. The caller is now the owner of the stretch. The starting address and length of the returned stretch may then be queried; these will always be a multiple of the machine's page size. The stretch is a part of protection domain.

Memory protection operations are carried out by the application through the stretch interface. This talks directly to the low-level translation system via simple system calls; it is not necessary to communicate with the system domain. Protection can be carried out in this way due to the protection model chosen which includes explicit rights for "change permissions" operations. A light-weight validation process checks if the caller is authorised to perform an operation.

It is also necessary that the frame which is being used for mapping (or which is being unmapped) is validated. This involves ensuring that the calling domain owns the frame, and that the frame is not currently mapped or nailed. These conditions are checked by using the RamTab, which is a simple enough structure to be used by low-level code.

Protection is carried out at stretch granularity -- every protection domain provides a mapping from the set of valid stretches to a subset of read, write, execute, meta. A domain which holds the meta right is authorised to modify protections and mappings on the relevant stretch. Domain may grant read/write/execute to another domain, if needed. Meta is only available to the owner and can be passed to one domain at a time only.

The accessibility of a stretch is determined by a combination of two things: the permissions for the stretch in the current protection domain and the global permissions of the stretch. The global permissions specify a minimum level of access that all domains share.


Translation system

The translation system deals with inserting, retrieving or deleting mappings between virtual and physical addresses. As such it may be considered an interface to a table of information held about these mappings; the actual mapping will typically be performed as necessary by whatever memory management hardware or software is present.

The translation system is divided into two parts: a high-level management module, and the low-level trap handlers and system calls. The high-level part is private to the system domain, and handles the following:

Bootstrapping the MMU (in hardware or software), and setting up initial mappings, 
Adding, modifying or deleting ranges of virtual addresses, and performing the associated page table management, 

Creating and deleting protection domains, 

Initialising and partly maintaining the RamTab; this is a simple data structure that maintains information about the current use of frames of main memory. 

The high-level translation system is used by both the stretch allocator and the frames allocator. The stretch allocator uses it to setup initial entries in the page table for stretches it has created, or to remove such entries when a stretch is destroyed. These entries contain protection information but are by default invalid: i.e. addresses within the range will cause a page fault if accessed.

Placing this functionality within the system domain means that the low-level translation system does not need to be concerned with the allocation of page-table memory. It also allows protection faults, page faults and "unallocated address" faults to be distinguished and dispatched to the faulting application. The frames allocator, on the other hand, uses the RamTab to record the owner and logical frame width of allocated frames of main memory.

Stretch driver is located inside application space, provided by the shared library code or implemented by the application itself. It interfaces with frame allocator to provide backing RAM storage for stretches it manages.

User domain calls map/unmap from the stretch driver. Either mapping or unmapping a virtual address "va" requires that the calling domain is executing in a protection domain which holds a meta right for the stretch containing "va". A consequence of this is that it is not possible to map a virtual address which is not part of some stretch.


Kickstart

Kickstart does all preinitialization work needed to get system going - it creates a system privileged domain, initializes the MMU and boots processors, then gives control to the boot modules loader. Module loader will resolve module dependencies, determine load order and load the TCB modules — these are the most important system modules, always trusted by other components.


Glue code

Glue code performs only a minimally necessary subset of operations that require privileged CPU mode. This includes manipulating MMU tables and switching protection domains. This code is therefore not preemptible.


Code exists in glue layer for a number of reasons:

code is privileged and therefore needs to execute with supervisor permissions, 

code is executed because of exception or interrupt and therefore needs to be both privileged and uninterruptible, 

code is generally used and needs to run atomically/uninterruptible. 

Interrupts and exception handlers are also implemented as stubs in glue code, due to their privileged nature.

Some glue code syscalls are privileged and can be used only by members of the TCB, others are used by application processes to request work from other domains.


Trusted Computing Base

TCB components implement features absolutely necessary for application functioning and therefore define the OS kernel.

Kernel components have almost no private data, on which contention could arise. Most of the data for kernel calls is provided by the process engaged in the syscall, therefore not affecting service of other processes. This also helps API atomicity.

Components export functionality through one or more interfaces. Kernel and userspace components are accessed via interfaces alike.


Library Components

Library components define the base substrate upon which the whole applications are built. Library components are real components and they export typed interfaces just like any other component does. Most library components are colocated into the same protection domain as the application using them.

Dynamic loader (Sjofn), similar to OMOS server, is used to perform component relocation and linking. Employed memory and loading models allow to share code and static data between all domains efficiently.

Meta-objects (in OMOS sense) are used to create generator interfaces which instantiate modules, used by application.

Applications

Components are pieces of code and static data (which has no mutable state). (Clemens Szypersky defines a software component as a unit of composition with contractually specified interfaces and explicit context dependencies only.)

Applications are built from interconnected components.

Applications consist of standard and custom components, which provide most of the functionality and main driver code. Applications service themselves - i.e. they service their own page faults or CPU scheduling decisions, often using standard components that provide necessary functionality already.

During startup application receives it's own domain, protection domain, initially not shared with any other domains a set of pervasives, among them a naming context which it can use to find other necessary components, a virtual CPU interface which it can use to make scheduling decisions (and also a scheduling domain, that represents this VCPU), a stretch and heap interfaces which it can use to allocate memory.

Applications run in domains. The kernel's view of a domain is limited to a single data structure called the Domain Control Block. Kernel uses DCBs to schedule domains' CPU time and other resources.


Interfaces

All interfaces are strongly typed, and these types are defined in an interface definition language. It is clearly important, therefore, to start with a good type system, and [Evers93] presents a good discussion of the issues of typing in a systems environment. The type system used in Metta is a hybrid: it includes notions both of the abstract types of interfaces and of concrete data types. It represents a compromise between the conceptual elegance and software engineering benefits of purely abstract type systems such as that used in Emerald [Raj91], and the requirements of efficiency and inter-operability: the goal is to implement an operating system with few restrictions on programming language.

Concrete types are data types whose structure is explicit. They can be predefined (such as booleans, strings, and integers of various sizes) or constructed (as with records, sequences, etc). The space of concrete types also includes typed references to interfaces.

Interfaces are instances of ADTs. Interfaces are rarely static: they can be dynamically created and references to them passed around freely. The type system includes a simple concept of subtyping. An interface type can be a subtype of another ADT, in which case it supports all the operations of the supertype, and an instance of the subtype can be used where an instance of the supertype is required.


The operations supported by interfaces are like procedure calls: they take a number of arguments and normally return a number of results. They can also raise exceptions, which themselves can take arguments.

An interface definition language is used to specify the types, exceptions and methods of an interface, and a run-time typesystem allows the narrowing of types and the marshaling of parameters for non-local procedure invocations.
Interfaces are defined in an IDL language called Meddle, a compiler named meddler will generate proper stubs from these IDL declarations. Interface compiler is based on LLVM framework together with the rest of JIT system.


Naming contexts

A name-space scheme (based on Plan-9 contexts) allows implementations of interfaces to be published and a trader component from the 
TCB may be used to find component(s) exporting a particular interface type or instance.
There are few restrictions on how the name space is structured. The model followed is that of [Saltzer79]: a name is a textual string, a binding is an association of a name with some value, and a context is a collection of bindings. Resolving a name is the process of locating the value bound to it. Name resolution requires that a context be specified. Context can bind names to other contexts, therefore providing a recursive tree-like structure.

VCPU

Virtual CPU interface allows domains to receive notifications when they are granted or revoked a CPU time slice or when a page fault or some other exception occurs.

VCPUs indeed perform inheritance scheduling - activation handler usually calls a scheduler function, which chooses next thread to run, by giving it the rest of CPU tick.

IDC

The only default mean of inter-domain communication is Event. Sending an event is a relatively lightweight operation, upon which many other syncronization and communication primitives may be built.

A networked IDC is also possible, given that component interfaces are generated from the IDL files, and therefore can provide marshalling and unmarshalling information for instantiating component interface stubs.


High-level architecture

High-level functionality is provided by standard components and applications comprising Metta backbone.

Exocortex

Exocortex is your external memory and your world representation. As user application, exocortex is a coordinator of agent swarm, doing tasks on your behalf in all reaches of the internets. You can instruct agents to aggregate information from other sources into your exocortex and to publish your information to other media. This swarm implements centralised-decentralised model — whatever you want to publish is generated centrally by you, in your favourite application, in your home environment, then agents can publish, transfer, upload, and share your data across the net to blogs, video services, additional shadow storage etc. In the same manner, whatever agents find out, can be brought to one of your devices and then seamlessly synced between all your devices forming the exocortex. This way you do not have to go for the news, the news come to you. At the same time, things you create are bound to you centrally, as they are emitted from your exocortex and maintain your identity integrity — once you update something, you do not have to go out and update that bit everywhere, it is synced much like p2p networks share data.


People

People are connected in social circles or nets. These circles provide layers of content filtering. People in the far out circles have very little influence on the data scores. The first order circle is used to primarily filter content - your immediate contacts have the most influence on what gets to you and what comes from you. The notion of circles is orthogonal to access rights, so people in the first circle do not have to see your content.


Content

Content posting is in many formats, like in Tumblr, using various record "types" like Text, Photo, Quote, Link, Chat, Audio, Video. A text for example may be a small excerpt or a whole page or even entire article with typographic markup. While reading, people may annotate such posts (a-la Guzzy), enter their own tags. Tags are added to a whole record tag pool, matching tags from multiple users get higher ranking. People entering the same tags get their recommendation influence strengthened, improving cross-recommendation possibility. This is at the moment pretty manual, but I hope to improve it using agents working on behalf of people.

Recommendations

There are several types of recommendations: direct address (somebody recommends something to you), direct shared (somebody recommends something to all) and indirect (somebody marked something as interesting, by starring it, rating it, writing a review, adding to favourites, pinning etc) People can rate the recommendation itself, by approving it, ignoring or rejecting it. Result of this action affects how the same type of recommendations from the same user will be treated in the future. So builds the recommendation network.


Contexts

http://www.remem.org/ The Remembrance Agent - Context data miner.

http://en.wikipedia.org/wiki/Memex - Associative trails

Contexts - the kind of activity you have at your computer. For example, a Chat context would definitely enable all popups and sounds and open multiple chat windows and have a browser preloaded in case your peers share some links. On the other hand a Presentation context will suppress all popups (your colleagues love to see these "Oh, honey, it was great last night" bubbles during presentations or even worse, don't they?), set your status as DND everywhere, suppress sounds and other programs like wifi password dialogs - all you don't need to get in the way when giving presentation. A Screensaver context would kick in when screensaver activates or you lock the screen manually. It will set you to Away everywhere (or even Not Available - depending on options available in particular IM protocol), it will reserve whole screen space for running the screensaver app - no more popups getting through the screensaver like it sometimes happens on X11 with badly written apps, and run it with specified process priority. You can have a Browsing context for example, too. It will fire up your favourite browser(s), have it open the sites you read regularly without need to reopen tabs or load a saved web profile manually.

Hope you can see the power of contexts already.


Data

Exocortex data is constantly persisted. You may force local data to be forgotten, but it may be reconstructed later based on its links.

"Ambient communication". You don't really have "programs" for communication, the protocol handlers will install at lower level and communicate using a low-level Common Protocol similar to Telepathy-over-DBus.

The user interface part of this communication can be manyfold, for example there's a notion of centralised contact list called (surprise) the Address Book, dubbed Contacts in Metta, because it contains entities you are communicating with.
Address Book gathers all contact information about your peers, so it's just as easy to send an osdev forum PM, SMS or a gtalk message from the same address book entry. Mail or incoming messages handling is done in the same way - you can open your contact in address book and see through recent history or unread, incoming or even dig deeper for older messages from them. Much like gmail interface keeps track of your conversations, address book is the entry point to everything that happens between you two. Even more - a group of people, such as a skype group chat or IRC chat room. Or your organization's structural unit, which is no different. Of course, there will be a way to stay alert of current incoming conversations, with popups and sounds and however else you configure it for yourself. Your peers are connected into a social graph, with multiple levels and different relations between them and other entities. Metta helps manage these graphs with ease.



Data exchange

sa devices interchanging data when in proximity. find url.
-- @todo organize --
amines — little agents that bind social services to exocortex. Mettamphetamine - main driver Dopplamine - doppler binding Twittamine - twitter binding etc Tryptamine - googlewave binding? :D

Xanadu 17 rules:

Every Xanadu server is uniquely and securely identified. 

Every Xanadu server can be operated independently or in a network. 

Every user is uniquely and securely identified. 

Every user can search, retrieve, create and store documents. 

Every document can consist of any number of parts each of which may be of any data type. 

Every document can contain links of any type including virtual copies ("transclusions") to any other document in the system accessible to its owner. 

Links are visible and can be followed from all endpoints. 

Permission to link to a document is explicitly granted by the act of publication. 

Every document can contain a royalty mechanism at any desired degree of granularity to ensure payment on any portion accessed, including virtual copies ("transclusions") of all or part of the document. 

Every document is uniquely and securely identified. 

Every document can have secure access controls. 

Every document can be rapidly searched, stored and retrieved without user knowledge of where it is physically stored. 

Every document is automatically moved to physical storage appropriate to its frequency of access from any given location. 

Every document is automatically stored redundantly to maintain availability even in case of a disaster. 

Every Xanadu service provider can charge their users at any rate they choose for the storage, retrieval and publishing of documents. 
Every transaction is secure and auditable only by the parties to that transaction. 

The Xanadu client-server communication protocol is an openly published standard. Third-party software development and integration is encouraged. 

